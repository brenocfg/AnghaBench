#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int hx509_query_option ;
struct TYPE_3__ {int /*<<< orphan*/  match; } ;
typedef  TYPE_1__ hx509_query ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_QUERY_KU_DIGITALSIGNATURE ; 
 int /*<<< orphan*/  HX509_QUERY_KU_ENCIPHERMENT ; 
 int /*<<< orphan*/  HX509_QUERY_KU_KEYCERTSIGN ; 
#define  HX509_QUERY_OPTION_END 132 
#define  HX509_QUERY_OPTION_KU_DIGITALSIGNATURE 131 
#define  HX509_QUERY_OPTION_KU_ENCIPHERMENT 130 
#define  HX509_QUERY_OPTION_KU_KEYCERTSIGN 129 
#define  HX509_QUERY_OPTION_PRIVATE_KEY 128 
 int /*<<< orphan*/  HX509_QUERY_PRIVATE_KEY ; 

void
hx509_query_match_option(hx509_query *q, hx509_query_option option)
{
    switch(option) {
    case HX509_QUERY_OPTION_PRIVATE_KEY:
	q->match |= HX509_QUERY_PRIVATE_KEY;
	break;
    case HX509_QUERY_OPTION_KU_ENCIPHERMENT:
	q->match |= HX509_QUERY_KU_ENCIPHERMENT;
	break;
    case HX509_QUERY_OPTION_KU_DIGITALSIGNATURE:
	q->match |= HX509_QUERY_KU_DIGITALSIGNATURE;
	break;
    case HX509_QUERY_OPTION_KU_KEYCERTSIGN:
	q->match |= HX509_QUERY_KU_KEYCERTSIGN;
	break;
    case HX509_QUERY_OPTION_END:
    default:
	break;
    }
}