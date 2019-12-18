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
struct vendor_attribute {int attrib_type; size_t attrib_len; int /*<<< orphan*/  attrib_data; int /*<<< orphan*/  vendor_value; } ;
struct rad_handle {int chap_pass; int /*<<< orphan*/  out_created; } ;

/* Variables and functions */
 int RAD_MICROSOFT_MS_CHAP2_RESPONSE ; 
 int RAD_MICROSOFT_MS_CHAP_RESPONSE ; 
 int RAD_VENDOR_MICROSOFT ; 
 int /*<<< orphan*/  RAD_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  free (struct vendor_attribute*) ; 
 int /*<<< orphan*/  generr (struct rad_handle*,char*,...) ; 
 int /*<<< orphan*/  htonl (int) ; 
 struct vendor_attribute* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int put_raw_attr (struct rad_handle*,int /*<<< orphan*/ ,struct vendor_attribute*,size_t) ; 

int
rad_put_vendor_attr(struct rad_handle *h, int vendor, int type,
    const void *value, size_t len)
{
	struct vendor_attribute *attr;
	int res;

	if (!h->out_created) {
		generr(h, "Please call rad_create_request()"
		    " before putting attributes");
		return -1;
	}

	if ((attr = malloc(len + 6)) == NULL) {
		generr(h, "malloc failure (%zu bytes)", len + 6);
		return -1;
	}

	attr->vendor_value = htonl(vendor);
	attr->attrib_type = type;
	attr->attrib_len = len + 2;
	memcpy(attr->attrib_data, value, len);

	res = put_raw_attr(h, RAD_VENDOR_SPECIFIC, attr, len + 6);
	free(attr);
	if (res == 0 && vendor == RAD_VENDOR_MICROSOFT
	    && (type == RAD_MICROSOFT_MS_CHAP_RESPONSE
	    || type == RAD_MICROSOFT_MS_CHAP2_RESPONSE)) {
		h->chap_pass = 1;
	}
	return (res);
}