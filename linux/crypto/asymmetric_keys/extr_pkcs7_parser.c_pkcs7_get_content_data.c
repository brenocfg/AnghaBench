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
struct pkcs7_message {void* data; size_t data_len; size_t data_hdrlen; } ;

/* Variables and functions */
 int ENODATA ; 

int pkcs7_get_content_data(const struct pkcs7_message *pkcs7,
			   const void **_data, size_t *_data_len,
			   size_t *_headerlen)
{
	if (!pkcs7->data)
		return -ENODATA;

	*_data = pkcs7->data;
	*_data_len = pkcs7->data_len;
	if (_headerlen)
		*_headerlen = pkcs7->data_hdrlen;
	return 0;
}