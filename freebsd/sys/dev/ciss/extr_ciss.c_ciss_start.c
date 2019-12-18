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
struct ciss_request {int /*<<< orphan*/  cr_tag; struct ciss_command* cr_cc; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_tag; } ;
struct ciss_command {TYPE_1__ header; } ;

/* Variables and functions */
 int ciss_map_request (struct ciss_request*) ; 
 int /*<<< orphan*/  ciss_print_request (struct ciss_request*) ; 
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ciss_start(struct ciss_request *cr)
{
    struct ciss_command	*cc;	/* XXX debugging only */
    int			error;

    cc = cr->cr_cc;
    debug(2, "post command %d tag %d ", cr->cr_tag, cc->header.host_tag);

    /*
     * Map the request's data.
     */
    if ((error = ciss_map_request(cr)))
	return(error);

#if 0
    ciss_print_request(cr);
#endif

    return(0);
}