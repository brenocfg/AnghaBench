#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int* c_cc; } ;
struct TYPE_3__ {unsigned int* c_cc; } ;

/* Variables and functions */
 scalar_t__ DISABLED (unsigned int) ; 
 int UChar (unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* key_backspace ; 
 TYPE_2__ mode ; 
 TYPE_1__ oldmode ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
report(const char *name, int which, unsigned def)
{
    unsigned older, newer;
    char *p;

    newer = mode.c_cc[which];
    older = oldmode.c_cc[which];

    if (older == newer && older == def)
	return;

    (void) fprintf(stderr, "%s %s ", name, older == newer ? "is" : "set to");

    if (DISABLED(newer))
	(void) fprintf(stderr, "undef.\n");
    /*
     * Check 'delete' before 'backspace', since the key_backspace value
     * is ambiguous.
     */
    else if (newer == 0177)
	(void) fprintf(stderr, "delete.\n");
    else if ((p = key_backspace) != 0
	     && newer == (unsigned char) p[0]
	     && p[1] == '\0')
	(void) fprintf(stderr, "backspace.\n");
    else if (newer < 040) {
	newer ^= 0100;
	(void) fprintf(stderr, "control-%c (^%c).\n", UChar(newer), UChar(newer));
    } else
	(void) fprintf(stderr, "%c.\n", UChar(newer));
}