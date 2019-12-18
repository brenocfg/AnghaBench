#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct isis_spb_mcid {int /*<<< orphan*/ * digest; int /*<<< orphan*/  revision_lvl; int /*<<< orphan*/  name; int /*<<< orphan*/  format_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct isis_spb_mcid const) ; 
 scalar_t__ fn_printzp (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
isis_print_mcid(netdissect_options *ndo,
                const struct isis_spb_mcid *mcid)
{
  int i;

  ND_TCHECK(*mcid);
  ND_PRINT((ndo,  "ID: %d, Name: ", mcid->format_id));

  if (fn_printzp(ndo, mcid->name, 32, ndo->ndo_snapend))
    goto trunc;

  ND_PRINT((ndo, "\n\t              Lvl: %d", EXTRACT_16BITS(mcid->revision_lvl)));

  ND_PRINT((ndo,  ", Digest: "));

  for(i=0;i<16;i++)
    ND_PRINT((ndo, "%.2x ", mcid->digest[i]));

trunc:
  ND_PRINT((ndo, "%s", tstr));
}