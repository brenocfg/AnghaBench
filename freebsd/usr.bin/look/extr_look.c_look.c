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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 unsigned char* binary_search (int /*<<< orphan*/ *,unsigned char*,unsigned char*) ; 
 unsigned char* linear_search (int /*<<< orphan*/ *,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  print_from (int /*<<< orphan*/ *,unsigned char*,unsigned char*) ; 

__attribute__((used)) static int
look(wchar_t *string, unsigned char *front, unsigned char *back)
{

	front = binary_search(string, front, back);
	front = linear_search(string, front, back);

	if (front)
		print_from(string, front, back);
	return (front ? 0 : 1);
}