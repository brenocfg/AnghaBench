#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  is_delta; } ;
struct TYPE_4__ {TYPE_1__ packed; } ;
struct object_info {int* typep; unsigned long* sizep; int whence; TYPE_2__ u; } ;
struct object_id {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
typedef  enum input_source { ____Placeholder_input_source } input_source ;

/* Variables and functions */
#define  OI_LOOSE 129 
#define  OI_PACKED 128 
 unsigned long big_file_threshold ; 
 int incore ; 
 int loose ; 
 int oid_object_info_extended (int /*<<< orphan*/ ,struct object_id const*,struct object_info*,int /*<<< orphan*/ ) ; 
 int pack_non_delta ; 
 int stream_error ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static enum input_source istream_source(const struct object_id *oid,
					enum object_type *type,
					struct object_info *oi)
{
	unsigned long size;
	int status;

	oi->typep = type;
	oi->sizep = &size;
	status = oid_object_info_extended(the_repository, oid, oi, 0);
	if (status < 0)
		return stream_error;

	switch (oi->whence) {
	case OI_LOOSE:
		return loose;
	case OI_PACKED:
		if (!oi->u.packed.is_delta && big_file_threshold < size)
			return pack_non_delta;
		/* fallthru */
	default:
		return incore;
	}
}