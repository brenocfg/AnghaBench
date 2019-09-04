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
struct st_fcgi_record_header_t {void* contentLength; void* requestId; } ;

/* Variables and functions */
 void* htons (void*) ; 
 int /*<<< orphan*/  memcpy (struct st_fcgi_record_header_t*,void const*,int) ; 

__attribute__((used)) static void decode_header(struct st_fcgi_record_header_t *decoded, const void *s)
{
    memcpy(decoded, s, sizeof(*decoded));
    decoded->requestId = htons(decoded->requestId);
    decoded->contentLength = htons(decoded->contentLength);
}