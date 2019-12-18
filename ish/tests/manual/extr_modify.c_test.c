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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*,int) ; 
 int stub1 () ; 
 int stub2 () ; 
 int stub3 () ; 
 int stub4 () ; 

__attribute__((used)) static void test(char *code, const char *name) {
    printf("%-6s before: %d expected 1\n", name, ((int (*)()) code)());
    code[1] = 2;
    printf("%-6s after:  %d expected 2\n", name, ((int (*)()) code)());
}