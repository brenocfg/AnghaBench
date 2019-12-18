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
struct wpa_supplicant {char* dbus_groupobj_path; } ;
struct peer_group_data {char** paths; int nb_paths; int /*<<< orphan*/  error; int /*<<< orphan*/  wpa_s; TYPE_1__* info; } ;
struct p2p_group_config {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct p2p_group {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p_device_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 char** os_realloc_array (char**,int,int) ; 
 struct p2p_group_config* p2p_group_get_config (struct p2p_group*) ; 
 int /*<<< orphan*/  p2p_group_is_client_connected (struct p2p_group*,int /*<<< orphan*/ ) ; 
 struct wpa_supplicant* wpas_get_p2p_go_iface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int match_group_where_peer_is_client(struct p2p_group *group,
					    void *user_data)
{
	struct peer_group_data *data = user_data;
	const struct p2p_group_config *cfg;
	struct wpa_supplicant *wpa_s_go;
	char **paths;

	if (!p2p_group_is_client_connected(group, data->info->p2p_device_addr))
		return 1;

	cfg = p2p_group_get_config(group);

	wpa_s_go = wpas_get_p2p_go_iface(data->wpa_s, cfg->ssid,
					 cfg->ssid_len);
	if (wpa_s_go == NULL)
		return 1;

	paths = os_realloc_array(data->paths, data->nb_paths + 1,
				 sizeof(char *));
	if (paths == NULL)
		goto out_of_memory;

	data->paths = paths;
	data->paths[data->nb_paths] = wpa_s_go->dbus_groupobj_path;
	data->nb_paths++;

	return 1;

out_of_memory:
	data->error = ENOMEM;
	return 0;
}