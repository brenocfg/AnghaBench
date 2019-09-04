#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct walker_data {TYPE_1__* alt; } ;
struct walker {struct walker_data* data; } ;
struct ref {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int http_fetch_ref (int /*<<< orphan*/ ,struct ref*) ; 

__attribute__((used)) static int fetch_ref(struct walker *walker, struct ref *ref)
{
	struct walker_data *data = walker->data;
	return http_fetch_ref(data->alt->base, ref);
}