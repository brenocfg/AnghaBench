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
struct wpabuf {int dummy; } ;
struct wpa_config {int dummy; } ;
struct global_parse_data {int /*<<< orphan*/  name; scalar_t__ param1; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 struct wpabuf* wpabuf_parse_bin (char const*) ; 

__attribute__((used)) static int wpa_global_config_parse_bin(const struct global_parse_data *data,
				       struct wpa_config *config, int line,
				       const char *pos)
{
	struct wpabuf **dst, *tmp;

	tmp = wpabuf_parse_bin(pos);
	if (!tmp)
		return -1;

	dst = (struct wpabuf **) (((u8 *) config) + (long) data->param1);
	wpabuf_free(*dst);
	*dst = tmp;
	wpa_printf(MSG_DEBUG, "%s", data->name);

	return 0;
}