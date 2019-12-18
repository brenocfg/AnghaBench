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

long strnlen_user(const char *s, long n)
{
	unsigned long res, tmp;

	if (s == NULL)
		return 0;

	asm volatile(
	"       cmpnei  %1, 0           \n"
	"       bf      3f              \n"
	"1:     cmpnei  %0, 0           \n"
	"       bf      3f              \n"
	"2:     ldb     %3, (%1, 0)     \n"
	"       cmpnei  %3, 0           \n"
	"       bf      3f              \n"
	"       subi    %0,  1          \n"
	"       addi    %1,  1          \n"
	"       br      1b              \n"
	"3:     subu    %2, %0          \n"
	"       addi    %2,  1          \n"
	"       br      5f              \n"
	"4:     movi    %0, 0           \n"
	"       br      5f              \n"
	".section __ex_table, \"a\"     \n"
	".align   2                     \n"
	".long    2b, 4b                \n"
	".previous                      \n"
	"5:                             \n"
	: "=r"(n), "=r"(s), "=r"(res), "=r"(tmp)
	: "0"(n), "1"(s), "2"(n)
	: "memory", "cc");

	return res;
}