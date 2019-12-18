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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int C_CLASS_OTHER ; 
 int C_CLASS_WHITE ; 
 int C_CLASS_WORD ; 
 scalar_t__ Isspace (int /*<<< orphan*/ ) ; 
 scalar_t__ isword (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
c_to_class(Char ch)
{
    if (Isspace(ch))
        return C_CLASS_WHITE;

    if (isword(ch))
        return C_CLASS_WORD;

    return C_CLASS_OTHER;
}