#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_string ;
struct wpabuf {int dummy; } ;
struct upnp_wps_device_sm {int dummy; } ;
struct upnp_wps_device_interface {TYPE_2__* wps; } ;
struct TYPE_3__ {char* manufacturer; char* model_name; char const* model_number; char const* serial_number; } ;
struct TYPE_4__ {char* friendly_name; char const* manufacturer_url; char const* model_description; char const* model_url; char const* upc; int /*<<< orphan*/  uuid; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_strlen (char const*) ; 
 int /*<<< orphan*/  uuid_bin2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 
 char* wps_device_xml_postfix ; 
 char* wps_device_xml_prefix ; 
 int /*<<< orphan*/  xml_add_tagged_data (struct wpabuf*,char*,char const*) ; 
 int /*<<< orphan*/  xml_data_encode (struct wpabuf*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void format_wps_device_xml(struct upnp_wps_device_interface *iface,
				  struct upnp_wps_device_sm *sm,
				  struct wpabuf *buf)
{
	const char *s;
	char uuid_string[80];

	wpabuf_put_str(buf, wps_device_xml_prefix);

	/*
	 * Add required fields with default values if not configured. Add
	 * optional and recommended fields only if configured.
	 */
	s = iface->wps->friendly_name;
	s = ((s && *s) ? s : "WPS Access Point");
	xml_add_tagged_data(buf, "friendlyName", s);

	s = iface->wps->dev.manufacturer;
	s = ((s && *s) ? s : "");
	xml_add_tagged_data(buf, "manufacturer", s);

	if (iface->wps->manufacturer_url)
		xml_add_tagged_data(buf, "manufacturerURL",
				    iface->wps->manufacturer_url);

	if (iface->wps->model_description)
		xml_add_tagged_data(buf, "modelDescription",
				    iface->wps->model_description);

	s = iface->wps->dev.model_name;
	s = ((s && *s) ? s : "");
	xml_add_tagged_data(buf, "modelName", s);

	if (iface->wps->dev.model_number)
		xml_add_tagged_data(buf, "modelNumber",
				    iface->wps->dev.model_number);

	if (iface->wps->model_url)
		xml_add_tagged_data(buf, "modelURL", iface->wps->model_url);

	if (iface->wps->dev.serial_number)
		xml_add_tagged_data(buf, "serialNumber",
				    iface->wps->dev.serial_number);

	uuid_bin2str(iface->wps->uuid, uuid_string, sizeof(uuid_string));
	s = uuid_string;
	/* Need "uuid:" prefix, thus we can't use xml_add_tagged_data()
	 * easily...
	 */
	wpabuf_put_str(buf, "<UDN>uuid:");
	xml_data_encode(buf, s, os_strlen(s));
	wpabuf_put_str(buf, "</UDN>\n");

	if (iface->wps->upc)
		xml_add_tagged_data(buf, "UPC", iface->wps->upc);

	wpabuf_put_str(buf, wps_device_xml_postfix);
}