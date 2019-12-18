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
struct counter_device {int dummy; } ;
struct counter_count {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  enum counter_count_direction { ____Placeholder_counter_count_direction } counter_count_direction ;

/* Variables and functions */
 char** counter_count_direction_str ; 
 int /*<<< orphan*/  quad8_direction_get (struct counter_device*,struct counter_count*,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t quad8_count_direction_read(struct counter_device *counter,
	struct counter_count *count, void *priv, char *buf)
{
	enum counter_count_direction dir;

	quad8_direction_get(counter, count, &dir);

	return sprintf(buf, "%s\n", counter_count_direction_str[dir]);
}