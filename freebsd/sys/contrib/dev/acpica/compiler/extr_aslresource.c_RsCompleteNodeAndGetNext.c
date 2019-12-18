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
struct TYPE_7__ {int /*<<< orphan*/  ParseOpcode; } ;
struct TYPE_8__ {TYPE_1__ Asl; } ;
typedef  TYPE_2__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 TYPE_2__* ASL_GET_PEER_NODE (TYPE_2__*) ; 
 int /*<<< orphan*/  PARSEOP_DEFAULT_ARG ; 

ACPI_PARSE_OBJECT *
RsCompleteNodeAndGetNext (
    ACPI_PARSE_OBJECT       *Op)
{

    /* Mark this node unused */

    Op->Asl.ParseOpcode = PARSEOP_DEFAULT_ARG;

    /* Move on to the next peer node in the initializer list */

    return (ASL_GET_PEER_NODE (Op));
}