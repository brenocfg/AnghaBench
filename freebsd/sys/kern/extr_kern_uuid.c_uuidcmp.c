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
struct uuid {int dummy; } ;

/* Variables and functions */
 int memcmp (struct uuid const*,struct uuid const*,int) ; 

int
uuidcmp(const struct uuid *uuid1, const struct uuid *uuid2)
{

	return (memcmp(uuid1, uuid2, sizeof(struct uuid)));
}