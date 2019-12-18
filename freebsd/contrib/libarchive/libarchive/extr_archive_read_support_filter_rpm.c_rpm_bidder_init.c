#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rpm {int /*<<< orphan*/  state; } ;
struct archive_read_filter {char* name; struct rpm* data; TYPE_1__* archive; int /*<<< orphan*/  close; int /*<<< orphan*/ * skip; int /*<<< orphan*/  read; int /*<<< orphan*/  code; } ;
struct TYPE_2__ {int /*<<< orphan*/  archive; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FILTER_RPM ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ST_LEAD ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  rpm_filter_close ; 
 int /*<<< orphan*/  rpm_filter_read ; 

__attribute__((used)) static int
rpm_bidder_init(struct archive_read_filter *self)
{
	struct rpm   *rpm;

	self->code = ARCHIVE_FILTER_RPM;
	self->name = "rpm";
	self->read = rpm_filter_read;
	self->skip = NULL; /* not supported */
	self->close = rpm_filter_close;

	rpm = (struct rpm *)calloc(sizeof(*rpm), 1);
	if (rpm == NULL) {
		archive_set_error(&self->archive->archive, ENOMEM,
		    "Can't allocate data for rpm");
		return (ARCHIVE_FATAL);
	}

	self->data = rpm;
	rpm->state = ST_LEAD;

	return (ARCHIVE_OK);
}