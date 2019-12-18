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
struct http_ctx {int dummy; } ;
typedef  int curl_infotype ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
#define  CURLINFO_DATA_IN 135 
#define  CURLINFO_DATA_OUT 134 
#define  CURLINFO_END 133 
#define  CURLINFO_HEADER_IN 132 
#define  CURLINFO_HEADER_OUT 131 
#define  CURLINFO_SSL_DATA_IN 130 
#define  CURLINFO_SSL_DATA_OUT 129 
#define  CURLINFO_TEXT 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  debug_dump (struct http_ctx*,char*,char*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int curl_cb_debug(CURL *curl, curl_infotype info, char *buf, size_t len,
			 void *userdata)
{
	struct http_ctx *ctx = userdata;
	switch (info) {
	case CURLINFO_TEXT:
		debug_dump(ctx, "CURLINFO_TEXT", buf, len);
		break;
	case CURLINFO_HEADER_IN:
		debug_dump(ctx, "CURLINFO_HEADER_IN", buf, len);
		break;
	case CURLINFO_HEADER_OUT:
		debug_dump(ctx, "CURLINFO_HEADER_OUT", buf, len);
		break;
	case CURLINFO_DATA_IN:
		debug_dump(ctx, "CURLINFO_DATA_IN", buf, len);
		break;
	case CURLINFO_DATA_OUT:
		debug_dump(ctx, "CURLINFO_DATA_OUT", buf, len);
		break;
	case CURLINFO_SSL_DATA_IN:
		wpa_printf(MSG_DEBUG, "debug - CURLINFO_SSL_DATA_IN - %d",
			   (int) len);
		break;
	case CURLINFO_SSL_DATA_OUT:
		wpa_printf(MSG_DEBUG, "debug - CURLINFO_SSL_DATA_OUT - %d",
			   (int) len);
		break;
	case CURLINFO_END:
		wpa_printf(MSG_DEBUG, "debug - CURLINFO_END - %d",
			   (int) len);
		break;
	}
	return 0;
}