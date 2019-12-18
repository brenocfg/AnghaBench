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
struct uni_msg {int dummy; } ;
struct uni {int dummy; } ;
typedef  enum saal_sig { ____Placeholder_saal_sig } saal_sig ;

/* Variables and functions */
#define  SAAL_DATA_indication 133 
#define  SAAL_ESTABLISH_confirm 132 
#define  SAAL_ESTABLISH_indication 131 
#define  SAAL_RELEASE_confirm 130 
#define  SAAL_RELEASE_indication 129 
#define  SAAL_UDATA_indication 128 
 int /*<<< orphan*/  SIGO_SAAL_DATA_indication ; 
 int /*<<< orphan*/  SIGO_SAAL_ESTABLISH_confirm ; 
 int /*<<< orphan*/  SIGO_SAAL_ESTABLISH_indication ; 
 int /*<<< orphan*/  SIGO_SAAL_RELEASE_confirm ; 
 int /*<<< orphan*/  SIGO_SAAL_RELEASE_indication ; 
 int /*<<< orphan*/  SIGO_SAAL_UDATA_indication ; 
 int /*<<< orphan*/  UNI_FAC_ERR ; 
 int /*<<< orphan*/  VERBOSE (struct uni*,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  uni_enq_coord (struct uni*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uni_msg*) ; 
 int /*<<< orphan*/  uni_msg_destroy (struct uni_msg*) ; 

void
uni_saal_input(struct uni *uni, enum saal_sig sig, struct uni_msg *m)
{
	switch (sig) {

	  case SAAL_ESTABLISH_indication:
		if (m != NULL)
			uni_msg_destroy(m);
		uni_enq_coord(uni, SIGO_SAAL_ESTABLISH_indication, 0, NULL);
		break;

	  case SAAL_ESTABLISH_confirm:
		if (m != NULL)
			uni_msg_destroy(m);
		uni_enq_coord(uni, SIGO_SAAL_ESTABLISH_confirm, 0, NULL);
		break;

	  case SAAL_RELEASE_confirm:
		if (m != NULL)
			uni_msg_destroy(m);
		uni_enq_coord(uni, SIGO_SAAL_RELEASE_confirm, 0, NULL);
		break;

	  case SAAL_RELEASE_indication:
		if (m != NULL)
			uni_msg_destroy(m);
		uni_enq_coord(uni, SIGO_SAAL_RELEASE_indication, 0, NULL);
		break;

	  case SAAL_DATA_indication:
		uni_enq_coord(uni, SIGO_SAAL_DATA_indication, 0, m);
		break;

	  case SAAL_UDATA_indication:
		uni_enq_coord(uni, SIGO_SAAL_UDATA_indication, 0, m);
		break;

	  default:
		VERBOSE(uni, UNI_FAC_ERR, 1, "bogus saal signal %u", sig);
		if (m != NULL)
			uni_msg_destroy(m);
		break;
	}
}