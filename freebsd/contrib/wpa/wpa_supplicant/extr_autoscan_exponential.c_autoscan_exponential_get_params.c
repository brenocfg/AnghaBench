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
struct autoscan_exponential_data {void* limit; void* base; } ;

/* Variables and functions */
 void* atoi (char const*) ; 
 char* os_strchr (char const*,char) ; 

__attribute__((used)) static int
autoscan_exponential_get_params(struct autoscan_exponential_data *data,
				const char *params)
{
	const char *pos;

	if (params == NULL)
		return -1;

	data->base = atoi(params);

	pos = os_strchr(params, ':');
	if (pos == NULL)
		return -1;

	pos++;
	data->limit = atoi(pos);

	return 0;
}