#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_15__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  certname ;
struct TYPE_21__ {int /*<<< orphan*/  rdnSequence; } ;
struct TYPE_22__ {TYPE_1__ u; int /*<<< orphan*/  element; } ;
struct TYPE_23__ {TYPE_2__ directoryName; } ;
struct TYPE_29__ {TYPE_3__ u; scalar_t__ element; } ;
struct TYPE_28__ {unsigned int len; TYPE_7__* val; } ;
struct TYPE_20__ {scalar_t__ element; } ;
struct TYPE_27__ {TYPE_15__ base; scalar_t__ maximum; scalar_t__ minimum; } ;
struct TYPE_24__ {int /*<<< orphan*/  rdnSequence; } ;
struct TYPE_25__ {TYPE_4__ u; int /*<<< orphan*/  element; } ;
struct TYPE_26__ {TYPE_5__ subject; } ;
struct TYPE_19__ {TYPE_6__ tbsCertificate; } ;
typedef  TYPE_8__ GeneralSubtrees ;
typedef  TYPE_9__ GeneralName ;
typedef  TYPE_10__ Certificate ;

/* Variables and functions */
 int HX509_RANGE ; 
 scalar_t__ choice_GeneralName_directoryName ; 
 int match_alt_name (TYPE_15__*,TYPE_10__ const*,int*,int*) ; 
 int match_general_name (TYPE_15__*,TYPE_9__*,int*) ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  subject_null_p (TYPE_10__ const*) ; 

__attribute__((used)) static int
match_tree(const GeneralSubtrees *t, const Certificate *c, int *match)
{
    int name, alt_name, same;
    unsigned int i;
    int ret = 0;

    name = alt_name = same = *match = 0;
    for (i = 0; i < t->len; i++) {
	if (t->val[i].minimum && t->val[i].maximum)
	    return HX509_RANGE;

	/*
	 * If the constraint apply to directoryNames, test is with
	 * subjectName of the certificate if the certificate have a
	 * non-null (empty) subjectName.
	 */

	if (t->val[i].base.element == choice_GeneralName_directoryName
	    && !subject_null_p(c))
	{
	    GeneralName certname;

	    memset(&certname, 0, sizeof(certname));
	    certname.element = choice_GeneralName_directoryName;
	    certname.u.directoryName.element =
		c->tbsCertificate.subject.element;
	    certname.u.directoryName.u.rdnSequence =
		c->tbsCertificate.subject.u.rdnSequence;

	    ret = match_general_name(&t->val[i].base, &certname, &name);
	}

	/* Handle subjectAltNames, this is icky since they
	 * restrictions only apply if the subjectAltName is of the
	 * same type. So if there have been a match of type, require
	 * altname to be set.
	 */
	ret = match_alt_name(&t->val[i].base, c, &same, &alt_name);
    }
    if (name && (!same || alt_name))
	*match = 1;
    return ret;
}