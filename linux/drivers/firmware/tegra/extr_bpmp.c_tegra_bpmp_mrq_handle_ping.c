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
struct tegra_bpmp_channel {TYPE_1__* ib; } ;
struct mrq_ping_response {int reply; } ;
struct mrq_ping_request {int challenge; } ;
typedef  int /*<<< orphan*/  response ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mrq_ping_response*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tegra_bpmp_mrq_return (struct tegra_bpmp_channel*,int /*<<< orphan*/ ,struct mrq_ping_response*,int) ; 

__attribute__((used)) static void tegra_bpmp_mrq_handle_ping(unsigned int mrq,
				       struct tegra_bpmp_channel *channel,
				       void *data)
{
	struct mrq_ping_request *request;
	struct mrq_ping_response response;

	request = (struct mrq_ping_request *)channel->ib->data;

	memset(&response, 0, sizeof(response));
	response.reply = request->challenge << 1;

	tegra_bpmp_mrq_return(channel, 0, &response, sizeof(response));
}