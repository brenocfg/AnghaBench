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
typedef  int /*<<< orphan*/  TERMTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,char*) ; 
 char* term_description (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
deschook(int db_index, int db_limit, const char *term_name, TERMTYPE *tp)
{
    (void) db_index;
    (void) db_limit;
    (void) printf("%-10s\t%s\n", term_name, term_description(tp));
}