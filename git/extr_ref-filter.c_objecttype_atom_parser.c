#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct used_atom {char* name; } ;
struct strbuf {int dummy; } ;
struct ref_format {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * typep; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; TYPE_2__ info; } ;
struct TYPE_5__ {int /*<<< orphan*/ * typep; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_4__ oi ; 
 TYPE_3__ oi_deref ; 
 int strbuf_addf_ret (struct strbuf*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int objecttype_atom_parser(const struct ref_format *format, struct used_atom *atom,
				  const char *arg, struct strbuf *err)
{
	if (arg)
		return strbuf_addf_ret(err, -1, _("%%(objecttype) does not take arguments"));
	if (*atom->name == '*')
		oi_deref.info.typep = &oi_deref.type;
	else
		oi.info.typep = &oi.type;
	return 0;
}