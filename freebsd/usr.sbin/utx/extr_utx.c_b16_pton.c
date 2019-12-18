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
 int /*<<< orphan*/  isxdigit (unsigned char) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,char*) ; 

__attribute__((used)) static int
b16_pton(const char *in, char *out, size_t len)
{
	size_t i;

	for (i = 0; i < len * 2; i++)
		if (!isxdigit((unsigned char)in[i]))
			return (1);
	for (i = 0; i < len; i++)
		sscanf(&in[i * 2], "%02hhx", &out[i]);
	return (0);
}