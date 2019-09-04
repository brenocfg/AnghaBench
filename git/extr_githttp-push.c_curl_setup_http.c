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
struct TYPE_2__ {int len; } ;
struct buffer {TYPE_1__ buf; } ;
typedef  int curl_write_callback ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int /*<<< orphan*/  CURLOPT_CUSTOMREQUEST ; 
 int /*<<< orphan*/  CURLOPT_INFILE ; 
 int /*<<< orphan*/  CURLOPT_INFILESIZE ; 
 int /*<<< orphan*/  CURLOPT_IOCTLDATA ; 
 int /*<<< orphan*/  CURLOPT_IOCTLFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_NOBODY ; 
 int /*<<< orphan*/  CURLOPT_PUT ; 
 int /*<<< orphan*/  CURLOPT_READFUNCTION ; 
 int /*<<< orphan*/  CURLOPT_UPLOAD ; 
 int /*<<< orphan*/  CURLOPT_URL ; 
 int /*<<< orphan*/  CURLOPT_WRITEFUNCTION ; 
 int /*<<< orphan*/  curl_easy_setopt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int fread_buffer ; 
 int ioctl_buffer ; 

__attribute__((used)) static void curl_setup_http(CURL *curl, const char *url,
		const char *custom_req, struct buffer *buffer,
		curl_write_callback write_fn)
{
	curl_easy_setopt(curl, CURLOPT_PUT, 1);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_INFILE, buffer);
	curl_easy_setopt(curl, CURLOPT_INFILESIZE, buffer->buf.len);
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, fread_buffer);
#ifndef NO_CURL_IOCTL
	curl_easy_setopt(curl, CURLOPT_IOCTLFUNCTION, ioctl_buffer);
	curl_easy_setopt(curl, CURLOPT_IOCTLDATA, buffer);
#endif
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_fn);
	curl_easy_setopt(curl, CURLOPT_NOBODY, 0);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, custom_req);
	curl_easy_setopt(curl, CURLOPT_UPLOAD, 1);
}