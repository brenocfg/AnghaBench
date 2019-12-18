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
struct intr_map_data {int type; size_t len; } ;
typedef  enum intr_map_data_type { ____Placeholder_intr_map_data_type } intr_map_data_type ;

/* Variables and functions */
 int /*<<< orphan*/  M_INTRNG ; 
 struct intr_map_data* malloc (size_t,int /*<<< orphan*/ ,int) ; 

struct intr_map_data *
intr_alloc_map_data(enum intr_map_data_type type, size_t len, int flags)
{
	struct intr_map_data *data;

	data = malloc(len, M_INTRNG, flags);
	data->type = type;
	data->len = len;
	return (data);
}