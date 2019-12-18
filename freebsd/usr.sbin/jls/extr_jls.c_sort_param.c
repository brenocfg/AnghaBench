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
struct jailparam {int /*<<< orphan*/  jp_name; } ;

/* Variables and functions */
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sort_param(const void *a, const void *b)
{
	const struct jailparam *parama, *paramb;
	char *ap, *bp;

	/* Put top-level parameters first. */
	parama = a;
	paramb = b;
	ap = strchr(parama->jp_name, '.');
	bp = strchr(paramb->jp_name, '.');
	if (ap && !bp)
		return (1);
	if (bp && !ap)
		return (-1);
	return (strcmp(parama->jp_name, paramb->jp_name));
}