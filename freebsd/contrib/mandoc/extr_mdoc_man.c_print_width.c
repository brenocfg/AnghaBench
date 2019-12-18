#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct roffsu {scalar_t__ unit; int scale; } ;
struct roff_node {scalar_t__ type; char* string; } ;
struct mdoc_bl {char* width; scalar_t__ type; int count; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int* Bl_stack ; 
 int /*<<< orphan*/  Bl_stack_len ; 
 scalar_t__ LIST_enum ; 
 scalar_t__ LIST_hang ; 
 scalar_t__ LIST_tag ; 
 scalar_t__ ROFFT_TEXT ; 
 scalar_t__ SCALE_EN ; 
 int /*<<< orphan*/  SCALE_MAX ; 
 int TPremain ; 
 char* a2roffsu (char*,struct roffsu*,int /*<<< orphan*/ ) ; 
 int man_strlen (char*) ; 
 int /*<<< orphan*/  mid_it () ; 
 int /*<<< orphan*/  print_block (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_word (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
print_width(const struct mdoc_bl *bl, const struct roff_node *child)
{
	char		  buf[24];
	struct roffsu	  su;
	const char	 *end;
	int		  numeric, remain, sz, chsz;

	numeric = 1;
	remain = 0;

	/* Convert the width into a number (of characters). */
	if (bl->width == NULL)
		sz = (bl->type == LIST_hang) ? 6 : 0;
	else {
		end = a2roffsu(bl->width, &su, SCALE_MAX);
		if (end == NULL || *end != '\0')
			sz = man_strlen(bl->width);
		else if (SCALE_EN == su.unit)
			sz = su.scale;
		else {
			sz = 0;
			numeric = 0;
		}
	}

	/* XXX Rough estimation, might have multiple parts. */
	if (bl->type == LIST_enum)
		chsz = (bl->count > 8) + 1;
	else if (child != NULL && child->type == ROFFT_TEXT)
		chsz = man_strlen(child->string);
	else
		chsz = 0;

	/* Maybe we are inside an enclosing list? */
	mid_it();

	/*
	 * Save our own indentation,
	 * such that child lists can use it.
	 */
	Bl_stack[Bl_stack_len++] = sz + 2;

	/* Set up the current list. */
	if (chsz > sz && bl->type != LIST_tag)
		print_block(".HP", 0);
	else {
		print_block(".TP", 0);
		remain = sz + 2;
	}
	if (numeric) {
		(void)snprintf(buf, sizeof(buf), "%dn", sz + 2);
		print_word(buf);
	} else
		print_word(bl->width);
	TPremain = remain;
}