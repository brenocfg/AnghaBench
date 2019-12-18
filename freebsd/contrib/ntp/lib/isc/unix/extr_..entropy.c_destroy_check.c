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
struct TYPE_7__ {int type; } ;
typedef  TYPE_1__ isc_entropysource_t ;
struct TYPE_8__ {scalar_t__ refcnt; int /*<<< orphan*/  sources; } ;
typedef  TYPE_2__ isc_entropy_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
#define  ENTROPY_SOURCETYPE_FILE 129 
#define  ENTROPY_SOURCETYPE_USOCKET 128 
 int /*<<< orphan*/  ISC_FALSE ; 
 TYPE_1__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_1__* ISC_LIST_NEXT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static inline isc_boolean_t
destroy_check(isc_entropy_t *ent) {
	isc_entropysource_t *source;

	if (ent->refcnt > 0)
		return (ISC_FALSE);

	source = ISC_LIST_HEAD(ent->sources);
	while (source != NULL) {
		switch (source->type) {
		case ENTROPY_SOURCETYPE_FILE:
		case ENTROPY_SOURCETYPE_USOCKET:
			break;
		default:
			return (ISC_FALSE);
		}
		source = ISC_LIST_NEXT(source, link);
	}

	return (ISC_TRUE);
}