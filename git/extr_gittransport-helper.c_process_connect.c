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
struct transport {struct helper_data* data; } ;
struct TYPE_2__ {char* receivepack; char* uploadpack; } ;
struct helper_data {TYPE_1__ transport_options; } ;

/* Variables and functions */
 int process_connect_service (struct transport*,char const*,char const*) ; 

__attribute__((used)) static int process_connect(struct transport *transport,
				     int for_push)
{
	struct helper_data *data = transport->data;
	const char *name;
	const char *exec;

	name = for_push ? "git-receive-pack" : "git-upload-pack";
	if (for_push)
		exec = data->transport_options.receivepack;
	else
		exec = data->transport_options.uploadpack;

	return process_connect_service(transport, name, exec);
}