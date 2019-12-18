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
struct ikev2_responder_data {int state; } ;

/* Variables and functions */
#define  CHILD_SA 133 
#define  IKEV2_DONE 132 
#define  IKEV2_FAILED 131 
#define  NOTIFY 130 
#define  SA_AUTH 129 
#define  SA_INIT 128 
 struct wpabuf* ikev2_build_notify (struct ikev2_responder_data*) ; 
 struct wpabuf* ikev2_build_sa_auth (struct ikev2_responder_data*) ; 
 struct wpabuf* ikev2_build_sa_init (struct ikev2_responder_data*) ; 

struct wpabuf * ikev2_responder_build(struct ikev2_responder_data *data)
{
	switch (data->state) {
	case SA_INIT:
		return ikev2_build_sa_init(data);
	case SA_AUTH:
		return ikev2_build_sa_auth(data);
	case CHILD_SA:
		return NULL;
	case NOTIFY:
		return ikev2_build_notify(data);
	case IKEV2_DONE:
	case IKEV2_FAILED:
		return NULL;
	}
	return NULL;
}