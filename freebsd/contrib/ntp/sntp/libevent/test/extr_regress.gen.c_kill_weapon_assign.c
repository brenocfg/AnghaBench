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
struct kill {int weapon_set; int /*<<< orphan*/ * weapon_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

int
kill_weapon_assign(struct kill *msg,
    const char * value)
{
  if (msg->weapon_data != NULL)
    free(msg->weapon_data);
  if ((msg->weapon_data = strdup(value)) == NULL)
    return (-1);
  msg->weapon_set = 1;
  return (0);
}