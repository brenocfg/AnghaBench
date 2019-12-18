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
struct bgscan_simple_data {void* long_interval; void* signal_threshold; void* short_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 void* atoi (char const*) ; 
 char* os_strchr (char const*,char) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int bgscan_simple_get_params(struct bgscan_simple_data *data,
				    const char *params)
{
	const char *pos;

	data->short_interval = atoi(params);

	pos = os_strchr(params, ':');
	if (pos == NULL)
		return 0;
	pos++;
	data->signal_threshold = atoi(pos);
	pos = os_strchr(pos, ':');
	if (pos == NULL) {
		wpa_printf(MSG_ERROR, "bgscan simple: Missing scan interval "
			   "for high signal");
		return -1;
	}
	pos++;
	data->long_interval = atoi(pos);

	return 0;
}