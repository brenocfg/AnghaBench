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
struct eap_teap_data {int dummy; } ;
typedef  enum teap_error_codes { ____Placeholder_teap_error_codes } teap_error_codes ;
typedef  int /*<<< orphan*/  EapType ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_NONE ; 
 int /*<<< orphan*/  FAILURE_SEND_RESULT ; 
 int /*<<< orphan*/  eap_teap_state (struct eap_teap_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static EapType eap_teap_req_failure(struct eap_teap_data *data,
				    enum teap_error_codes error)
{
	eap_teap_state(data, FAILURE_SEND_RESULT);
	return EAP_TYPE_NONE;
}