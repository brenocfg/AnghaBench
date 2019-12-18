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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int parse_integer (int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int
parse_threadid(const uint8_t *data, size_t len)
{

	if (len == 1 && *data == '0')
		return (0);
	if (len == 2 && memcmp(data, "-1", 2) == 0)
		return (-1);
	if (len == 0)
		return (-2);
	return (parse_integer(data, len));
}