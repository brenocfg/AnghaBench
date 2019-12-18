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
struct keys {int dummy; } ;

/* Variables and functions */
 struct keys* calloc (int,int) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 

struct keys *
keys_new(void)
{
	struct keys *keys;

	keys = calloc(1, sizeof(*keys));
	if (keys == NULL)
		log_err(1, "calloc");

	return (keys);
}