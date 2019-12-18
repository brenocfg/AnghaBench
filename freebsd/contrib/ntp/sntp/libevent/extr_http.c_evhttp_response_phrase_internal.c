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
struct TYPE_3__ {char const* name; char const** responses; scalar_t__ num_responses; } ;

/* Variables and functions */
 scalar_t__ MEMBERSOF (TYPE_1__*) ; 
 TYPE_1__* response_classes ; 

__attribute__((used)) static const char *
evhttp_response_phrase_internal(int code)
{
	int klass = code / 100 - 1;
	int subcode = code % 100;

	/* Unknown class - can't do any better here */
	if (klass < 0 || klass >= (int) MEMBERSOF(response_classes))
		return "Unknown Status Class";

	/* Unknown sub-code, return class name at least */
	if (subcode >= (int) response_classes[klass].num_responses)
		return response_classes[klass].name;

	return response_classes[klass].responses[subcode];
}