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
struct TYPE_2__ {int /*<<< orphan*/ * scratch_buffer; } ;
struct worker {TYPE_1__ env; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  load_rrset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct worker*) ; 
 int /*<<< orphan*/  read_fixed (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ ssl_read_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
load_rrset_cache(RES* ssl, struct worker* worker)
{
	sldns_buffer* buf = worker->env.scratch_buffer;
	if(!read_fixed(ssl, buf, "START_RRSET_CACHE")) return 0;
	while(ssl_read_buf(ssl, buf) && 
		strcmp((char*)sldns_buffer_begin(buf), "END_RRSET_CACHE")!=0) {
		if(!load_rrset(ssl, buf, worker))
			return 0;
	}
	return 1;
}