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
struct wpabuf {int dummy; } ;
struct eap_aka_data {int /*<<< orphan*/ * id_msgs; } ;

/* Variables and functions */
 int /*<<< orphan*/ * wpabuf_dup (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (int /*<<< orphan*/ *,struct wpabuf const*) ; 
 scalar_t__ wpabuf_resize (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eap_aka_add_id_msg(struct eap_aka_data *data,
			      const struct wpabuf *msg)
{
	if (msg == NULL)
		return -1;

	if (data->id_msgs == NULL) {
		data->id_msgs = wpabuf_dup(msg);
		return data->id_msgs == NULL ? -1 : 0;
	}

	if (wpabuf_resize(&data->id_msgs, wpabuf_len(msg)) < 0)
		return -1;
	wpabuf_put_buf(data->id_msgs, msg);

	return 0;
}