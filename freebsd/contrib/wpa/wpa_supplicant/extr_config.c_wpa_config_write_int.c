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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_ssid {int dummy; } ;
struct parse_data {scalar_t__ param1; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (int) ; 
 int os_snprintf (char*,int,char*,int) ; 
 scalar_t__ os_snprintf_error (int,int) ; 

__attribute__((used)) static char * wpa_config_write_int(const struct parse_data *data,
				   struct wpa_ssid *ssid)
{
	int *src, res;
	char *value;

	src = (int *) (((u8 *) ssid) + (long) data->param1);

	value = os_malloc(20);
	if (value == NULL)
		return NULL;
	res = os_snprintf(value, 20, "%d", *src);
	if (os_snprintf_error(20, res)) {
		os_free(value);
		return NULL;
	}
	value[20 - 1] = '\0';
	return value;
}