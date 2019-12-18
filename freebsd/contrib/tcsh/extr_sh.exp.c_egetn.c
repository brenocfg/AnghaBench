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
typedef  int /*<<< orphan*/  tcsh_number_t ;
typedef  char Char ;

/* Variables and functions */
 int ERR_EXPRESSION ; 
 int ERR_NAME ; 
 int /*<<< orphan*/  Isdigit (char const) ; 
 int /*<<< orphan*/  getn (char const*) ; 
 int /*<<< orphan*/  stderror (int) ; 

__attribute__((used)) static tcsh_number_t
egetn(const Char *cp)
{
    if (*cp && *cp != '-' && !Isdigit(*cp))
	stderror(ERR_NAME | ERR_EXPRESSION);
    return (getn(cp));
}