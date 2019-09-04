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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  strtoumax (char const*,char**,int) ; 

__attribute__((used)) static uint32_t strtouint32(const char *s)
{
	char *end;
	uintmax_t n = strtoumax(s, &end, 10);
	if (*s == '\0' || *end != '\0')
		die("invalid count: %s", s);
	return (uint32_t) n;
}