#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int start; int wptr; } ;
struct TYPE_8__ {int id; int flags; int qdcount; int ancount; int nscount; int arcount; } ;
struct TYPE_7__ {int rcode; TYPE_1__ Out; TYPE_3__ header; } ;
typedef  TYPE_2__ dns_response_t ;
typedef  TYPE_3__ dns_header_t ;
struct TYPE_9__ {int /*<<< orphan*/  rcode_refused_queries; int /*<<< orphan*/  rcode_not_implemented_queries; int /*<<< orphan*/  rcode_name_error_queries; int /*<<< orphan*/  rcode_server_failure_queries; int /*<<< orphan*/  rcode_format_queries; int /*<<< orphan*/  rcode_no_error_queries; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
#define  dns_rcode_format_error 133 
#define  dns_rcode_name_error 132 
#define  dns_rcode_no_error 131 
#define  dns_rcode_not_implemented 130 
#define  dns_rcode_refused 129 
#define  dns_rcode_server_failure 128 
 unsigned short htons (int) ; 
 TYPE_4__ wstat ; 

__attribute__((used)) static int dns_store_header (dns_response_t *r) {
  unsigned short *p = (unsigned short *) r->Out.start;
  dns_header_t *H = &r->header;
  switch (r->rcode) {
    case dns_rcode_no_error:
      wstat.rcode_no_error_queries++;
      break;
    case dns_rcode_format_error:
      wstat.rcode_format_queries++;
      break;
    case dns_rcode_server_failure:
      wstat.rcode_server_failure_queries++;
      break;
    case dns_rcode_name_error:
      wstat.rcode_name_error_queries++;
      break;
    case dns_rcode_not_implemented:
      wstat.rcode_not_implemented_queries++;
      break;
    case dns_rcode_refused:
      wstat.rcode_refused_queries++;
      break;
    default:
      assert (0);
  }
  p[0] = htons (H->id);
  H->flags |= r->rcode;
  p[1] = htons (H->flags);
  p[2] = htons (H->qdcount);
  p[3] = htons (H->ancount);
  p[4] = htons (H->nscount);
  p[5] = htons (H->arcount);
  return r->Out.wptr - r->Out.start;
}