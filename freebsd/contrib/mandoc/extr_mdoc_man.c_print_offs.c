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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__* Bl_stack ; 
 int Bl_stack_len ; 
 int /*<<< orphan*/  MMAN_Bk_susp ; 
 int /*<<< orphan*/  MMAN_nl ; 
 scalar_t__ SCALE_EN ; 
 char* a2roffsu (char const*,struct roffsu*,scalar_t__) ; 
 int man_strlen (char const*) ; 
 int /*<<< orphan*/  outflags ; 
 int /*<<< orphan*/  print_line (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_word (char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void
print_offs(const char *v, int keywords)
{
	char		  buf[24];
	struct roffsu	  su;
	const char	 *end;
	int		  sz;

	print_line(".RS", MMAN_Bk_susp);

	/* Convert v into a number (of characters). */
	if (NULL == v || '\0' == *v || (keywords && !strcmp(v, "left")))
		sz = 0;
	else if (keywords && !strcmp(v, "indent"))
		sz = 6;
	else if (keywords && !strcmp(v, "indent-two"))
		sz = 12;
	else {
		end = a2roffsu(v, &su, SCALE_EN);
		if (end == NULL || *end != '\0')
			sz = man_strlen(v);
		else if (SCALE_EN == su.unit)
			sz = su.scale;
		else {
			/*
			 * XXX
			 * If we are inside an enclosing list,
			 * there is no easy way to add the two
			 * indentations because they are provided
			 * in terms of different units.
			 */
			print_word(v);
			outflags |= MMAN_nl;
			return;
		}
	}

	/*
	 * We are inside an enclosing list.
	 * Add the two indentations.
	 */
	if (Bl_stack_len)
		sz += Bl_stack[Bl_stack_len - 1];

	(void)snprintf(buf, sizeof(buf), "%dn", sz);
	print_word(buf);
	outflags |= MMAN_nl;
}