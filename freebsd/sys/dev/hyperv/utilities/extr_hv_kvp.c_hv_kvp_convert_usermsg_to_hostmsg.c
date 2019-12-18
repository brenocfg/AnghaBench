#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_10__ {char* value; } ;
struct hv_kvp_exchg_msg_value {char* key; int key_size; int value_size; void* value_type; TYPE_5__ msg_value; } ;
struct TYPE_8__ {struct hv_kvp_exchg_msg_value data; } ;
struct TYPE_7__ {struct hv_kvp_exchg_msg_value data; } ;
struct TYPE_9__ {TYPE_3__ kvp_get; TYPE_2__ kvp_enum_data; } ;
struct TYPE_6__ {int operation; } ;
struct hv_kvp_msg {TYPE_4__ body; TYPE_1__ kvp_hdr; } ;
struct hv_kvp_ip_msg {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int HV_KVP_EXCHANGE_MAX_KEY_SIZE ; 
 int HV_KVP_EXCHANGE_MAX_VALUE_SIZE ; 
#define  HV_KVP_OP_DELETE 133 
#define  HV_KVP_OP_ENUMERATE 132 
#define  HV_KVP_OP_GET 131 
#define  HV_KVP_OP_GET_IP_INFO 130 
#define  HV_KVP_OP_SET 129 
#define  HV_KVP_OP_SET_IP_INFO 128 
 void* HV_REG_SZ ; 
 int hv_kvp_convert_utf8_ipinfo_to_utf16 (struct hv_kvp_msg*,struct hv_kvp_ip_msg*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int utf8_to_utf16 (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int
hv_kvp_convert_usermsg_to_hostmsg(struct hv_kvp_msg *umsg, struct hv_kvp_msg *hmsg)
{
	int hkey_len = 0, hvalue_len = 0, utf_err = 0;
	struct hv_kvp_exchg_msg_value *host_exchg_data;
	char *key_name, *value;

	struct hv_kvp_ip_msg *host_ip_msg = (struct hv_kvp_ip_msg *)hmsg;

	switch (hmsg->kvp_hdr.operation) {
	case HV_KVP_OP_GET_IP_INFO:
		return (hv_kvp_convert_utf8_ipinfo_to_utf16(umsg, host_ip_msg));

	case HV_KVP_OP_SET_IP_INFO:
	case HV_KVP_OP_SET:
	case HV_KVP_OP_DELETE:
		return (0);

	case HV_KVP_OP_ENUMERATE:
		host_exchg_data = &hmsg->body.kvp_enum_data.data;
		key_name = umsg->body.kvp_enum_data.data.key;
		hkey_len = utf8_to_utf16((uint16_t *)host_exchg_data->key,
				((HV_KVP_EXCHANGE_MAX_KEY_SIZE / 2) - 2),
				key_name, strlen(key_name),
				1, &utf_err);
		/* utf16 encoding */
		host_exchg_data->key_size = 2 * (hkey_len + 1);
		value = umsg->body.kvp_enum_data.data.msg_value.value;
		hvalue_len = utf8_to_utf16(
				(uint16_t *)host_exchg_data->msg_value.value,
				((HV_KVP_EXCHANGE_MAX_VALUE_SIZE / 2) - 2),
				value, strlen(value),
				1, &utf_err);
		host_exchg_data->value_size = 2 * (hvalue_len + 1);
		host_exchg_data->value_type = HV_REG_SZ;

		if ((hkey_len < 0) || (hvalue_len < 0))
			return (EINVAL);

		return (0);

	case HV_KVP_OP_GET:
		host_exchg_data = &hmsg->body.kvp_get.data;
		value = umsg->body.kvp_get.data.msg_value.value;
		hvalue_len = utf8_to_utf16(
				(uint16_t *)host_exchg_data->msg_value.value,
				((HV_KVP_EXCHANGE_MAX_VALUE_SIZE / 2) - 2),
				value, strlen(value),
				1, &utf_err);
		/* Convert value size to uft16 */
		host_exchg_data->value_size = 2 * (hvalue_len + 1);
		/* Use values by string */
		host_exchg_data->value_type = HV_REG_SZ;

		if (hvalue_len < 0)
			return (EINVAL);

		return (0);

	default:
		return (EINVAL);
	}
}