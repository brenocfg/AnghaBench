#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
struct TYPE_31__ {int /*<<< orphan*/  style; int /*<<< orphan*/  implicit; int /*<<< orphan*/  tag; int /*<<< orphan*/  anchor; } ;
struct TYPE_30__ {int /*<<< orphan*/  style; int /*<<< orphan*/  implicit; int /*<<< orphan*/  tag; int /*<<< orphan*/  anchor; } ;
struct TYPE_29__ {int /*<<< orphan*/  style; int /*<<< orphan*/  quoted_implicit; int /*<<< orphan*/  plain_implicit; int /*<<< orphan*/  length; int /*<<< orphan*/  value; int /*<<< orphan*/  tag; int /*<<< orphan*/  anchor; } ;
struct TYPE_28__ {int /*<<< orphan*/  anchor; } ;
struct TYPE_27__ {int /*<<< orphan*/  implicit; } ;
struct TYPE_25__ {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct TYPE_26__ {int /*<<< orphan*/  implicit; TYPE_2__ tag_directives; int /*<<< orphan*/  version_directive; } ;
struct TYPE_24__ {int /*<<< orphan*/  encoding; } ;
struct TYPE_32__ {TYPE_8__ mapping_start; TYPE_7__ sequence_start; TYPE_6__ scalar; TYPE_5__ alias; TYPE_4__ document_end; TYPE_3__ document_start; TYPE_1__ stream_start; } ;
struct TYPE_23__ {int type; TYPE_9__ data; } ;
typedef  TYPE_10__ yaml_event_t ;

/* Variables and functions */
#define  YAML_ALIAS_EVENT 137 
#define  YAML_DOCUMENT_END_EVENT 136 
#define  YAML_DOCUMENT_START_EVENT 135 
#define  YAML_MAPPING_END_EVENT 134 
#define  YAML_MAPPING_START_EVENT 133 
#define  YAML_SCALAR_EVENT 132 
#define  YAML_SEQUENCE_END_EVENT 131 
#define  YAML_SEQUENCE_START_EVENT 130 
#define  YAML_STREAM_END_EVENT 129 
#define  YAML_STREAM_START_EVENT 128 
 int /*<<< orphan*/  assert (int) ; 
 int yaml_alias_event_initialize (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int yaml_document_end_event_initialize (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int yaml_document_start_event_initialize (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int yaml_mapping_end_event_initialize (TYPE_10__*) ; 
 int yaml_mapping_start_event_initialize (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int yaml_scalar_event_initialize (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int yaml_sequence_end_event_initialize (TYPE_10__*) ; 
 int yaml_sequence_start_event_initialize (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int yaml_stream_end_event_initialize (TYPE_10__*) ; 
 int yaml_stream_start_event_initialize (TYPE_10__*,int /*<<< orphan*/ ) ; 

int copy_event(yaml_event_t *event_to, yaml_event_t *event_from)
{
    switch (event_from->type)
    {
        case YAML_STREAM_START_EVENT:
            return yaml_stream_start_event_initialize(event_to,
                    event_from->data.stream_start.encoding);

        case YAML_STREAM_END_EVENT:
            return yaml_stream_end_event_initialize(event_to);

        case YAML_DOCUMENT_START_EVENT:
            return yaml_document_start_event_initialize(event_to,
                    event_from->data.document_start.version_directive,
                    event_from->data.document_start.tag_directives.start,
                    event_from->data.document_start.tag_directives.end,
                    event_from->data.document_start.implicit);

        case YAML_DOCUMENT_END_EVENT:
            return yaml_document_end_event_initialize(event_to,
                    event_from->data.document_end.implicit);

        case YAML_ALIAS_EVENT:
            return yaml_alias_event_initialize(event_to,
                    event_from->data.alias.anchor);

        case YAML_SCALAR_EVENT:
            return yaml_scalar_event_initialize(event_to,
                    event_from->data.scalar.anchor,
                    event_from->data.scalar.tag,
                    event_from->data.scalar.value,
                    event_from->data.scalar.length,
                    event_from->data.scalar.plain_implicit,
                    event_from->data.scalar.quoted_implicit,
                    event_from->data.scalar.style);

        case YAML_SEQUENCE_START_EVENT:
            return yaml_sequence_start_event_initialize(event_to,
                    event_from->data.sequence_start.anchor,
                    event_from->data.sequence_start.tag,
                    event_from->data.sequence_start.implicit,
                    event_from->data.sequence_start.style);

        case YAML_SEQUENCE_END_EVENT:
            return yaml_sequence_end_event_initialize(event_to);

        case YAML_MAPPING_START_EVENT:
            return yaml_mapping_start_event_initialize(event_to,
                    event_from->data.mapping_start.anchor,
                    event_from->data.mapping_start.tag,
                    event_from->data.mapping_start.implicit,
                    event_from->data.mapping_start.style);

        case YAML_MAPPING_END_EVENT:
            return yaml_mapping_end_event_initialize(event_to);

        default:
            assert(1);
    }

    return 0;
}