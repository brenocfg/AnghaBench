#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int n_keys; } ;
typedef  TYPE_1__ keymap_t ;
struct TYPE_8__ {int n_accs; } ;
typedef  TYPE_2__ accentmap_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  TACC 129 
#define  TNUM 128 
 int /*<<< orphan*/  errx (int,char*) ; 
 int get_accent_definition_line (TYPE_2__*) ; 
 int get_key_definition_line (TYPE_1__*) ; 
 int token ; 
 int /*<<< orphan*/ * yyin ; 
 int yylex () ; 

__attribute__((used)) static int
get_definition_line(FILE *file, keymap_t *keymap, accentmap_t *accentmap)
{
	int c;

	yyin = file;

	if (token < 0)
		token = yylex();
	switch (token) { 
	case TNUM:
		c = get_key_definition_line(keymap);
		if (c < 0)
			errx(1, "invalid key definition");
		if (c > keymap->n_keys)
			keymap->n_keys = c;
		break;
	case TACC:
		c = get_accent_definition_line(accentmap);
		if (c < 0)
			errx(1, "invalid accent key definition");
		if (c > accentmap->n_accs)
			accentmap->n_accs = c;
		break;
	case 0:
		/* EOF */
		return -1;
	default:
		errx(1, "illegal definition line");
	}
	return c;
}