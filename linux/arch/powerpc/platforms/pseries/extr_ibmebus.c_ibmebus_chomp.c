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
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static char *ibmebus_chomp(const char *in, size_t count)
{
	char *out = kmalloc(count + 1, GFP_KERNEL);

	if (!out)
		return NULL;

	memcpy(out, in, count);
	out[count] = '\0';
	if (out[count - 1] == '\n')
		out[count - 1] = '\0';

	return out;
}