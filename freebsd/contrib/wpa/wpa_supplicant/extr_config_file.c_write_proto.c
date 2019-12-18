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
struct wpa_ssid {scalar_t__ proto; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ DEFAULT_PROTO ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* wpa_config_get (struct wpa_ssid*,char*) ; 

__attribute__((used)) static void write_proto(FILE *f, struct wpa_ssid *ssid)
{
	char *value;

	if (ssid->proto == DEFAULT_PROTO)
		return;

	value = wpa_config_get(ssid, "proto");
	if (value == NULL)
		return;
	if (value[0])
		fprintf(f, "\tproto=%s\n", value);
	os_free(value);
}