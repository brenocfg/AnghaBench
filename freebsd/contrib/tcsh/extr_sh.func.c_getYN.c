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
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 int /*<<< orphan*/  SHIN ; 
 int /*<<< orphan*/  flush () ; 
 int force_read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  xprintf (char*,char const*) ; 

int
getYN(const char *prompt)
{
    int doit;
    char c;

    xprintf("%s", prompt);
    flush();
    (void) force_read(SHIN, &c, sizeof(c));
    /* 
     * Perhaps we should use the yesexpr from the
     * actual locale
     */
    doit = (strchr(CGETS(22, 14, "Yy"), c) != NULL);
    while (c != '\n' && force_read(SHIN, &c, sizeof(c)) == sizeof(c))
	continue;
    return doit;
}