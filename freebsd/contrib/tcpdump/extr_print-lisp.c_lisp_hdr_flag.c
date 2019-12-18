#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;
struct TYPE_8__ {int /*<<< orphan*/  type_and_flag; } ;
typedef  TYPE_2__ lisp_map_register_hdr ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (TYPE_2__ const*) ; 
 scalar_t__ LISP_MAP_NOTIFY ; 
 scalar_t__ LISP_MAP_REGISTER ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  bittok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ extract_lisp_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lisp_type ; 
 int /*<<< orphan*/  map_notify_hdr_flag ; 
 int /*<<< orphan*/  map_register_hdr_flag ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void lisp_hdr_flag(netdissect_options *ndo, const lisp_map_register_hdr *lisp_hdr)
{
	uint8_t type = extract_lisp_type(lisp_hdr->type_and_flag);

	if (!ndo->ndo_vflag) {
		ND_PRINT((ndo, "%s,", tok2str(lisp_type, "unknown-type-%u", type)));
		return;
	} else {
		ND_PRINT((ndo, "%s,", tok2str(lisp_type, "unknown-type-%u", type)));
	}

	if (type == LISP_MAP_REGISTER) {
		ND_PRINT((ndo, " flags [%s],", bittok2str(map_register_hdr_flag,
			 "none", EXTRACT_32BITS(lisp_hdr))));
	} else if (type == LISP_MAP_NOTIFY) {
		ND_PRINT((ndo, " flags [%s],", bittok2str(map_notify_hdr_flag,
			 "none", EXTRACT_32BITS(lisp_hdr))));
	}

	return;
}