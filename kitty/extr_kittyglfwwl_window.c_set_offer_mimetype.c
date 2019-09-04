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
struct _GLFWWaylandDataOffer {char* mime; int is_self_offer; int has_uri_list; } ;

/* Variables and functions */
 char* URI_LIST_MIME ; 
 char* clipboard_mime () ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void set_offer_mimetype(struct _GLFWWaylandDataOffer* offer, const char* mime) {
    if (strcmp(mime, "text/plain;charset=utf-8") == 0)
        offer->mime = "text/plain;charset=utf-8";
    else if (!offer->mime && strcmp(mime, "text/plain") == 0)
        offer->mime = "text/plain";
    else if (strcmp(mime, clipboard_mime()) == 0)
        offer->is_self_offer = 1;
    else if (strcmp(mime, URI_LIST_MIME) == 0)
        offer->has_uri_list = 1;
}