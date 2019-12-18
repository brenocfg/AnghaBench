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
struct patch {int dummy; } ;

/* Variables and functions */
 struct patch* PATH_TO_BE_DELETED ; 

__attribute__((used)) static int to_be_deleted(struct patch *patch)
{
	return patch == PATH_TO_BE_DELETED;
}