#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_6__ {size_t length; struct TYPE_6__* data; } ;
struct TYPE_5__ {TYPE_3__* parameters; int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ DigestAlgorithmIdentifier ;

/* Variables and functions */
 int ENOMEM ; 
 int der_copy_oid (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,void const*,size_t) ; 

__attribute__((used)) static int
set_digest_alg(DigestAlgorithmIdentifier *id,
	       const heim_oid *oid,
	       const void *param, size_t length)
{
    int ret;
    if (param) {
	id->parameters = malloc(sizeof(*id->parameters));
	if (id->parameters == NULL)
	    return ENOMEM;
	id->parameters->data = malloc(length);
	if (id->parameters->data == NULL) {
	    free(id->parameters);
	    id->parameters = NULL;
	    return ENOMEM;
	}
	memcpy(id->parameters->data, param, length);
	id->parameters->length = length;
    } else
	id->parameters = NULL;
    ret = der_copy_oid(oid, &id->algorithm);
    if (ret) {
	if (id->parameters) {
	    free(id->parameters->data);
	    free(id->parameters);
	    id->parameters = NULL;
	}
	return ret;
    }
    return 0;
}