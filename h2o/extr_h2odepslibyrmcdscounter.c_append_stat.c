#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yrmcds_error ;
struct TYPE_6__ {int count; int capacity; TYPE_2__* records; } ;
typedef  TYPE_1__ yrmcds_cnt_statistics ;
struct TYPE_7__ {char const* name; char const* value; void* value_length; void* name_length; } ;
typedef  TYPE_2__ yrmcds_cnt_stat ;
typedef  void* uint16_t ;

/* Variables and functions */
 size_t INITIAL_STATS_CAPACITY ; 
 int /*<<< orphan*/  YRMCDS_OK ; 
 int /*<<< orphan*/  YRMCDS_OUT_OF_MEMORY ; 
 TYPE_2__* realloc (TYPE_2__*,int) ; 

__attribute__((used)) static yrmcds_error
append_stat(yrmcds_cnt_statistics* s,
            uint16_t name_len, uint16_t value_len,
            const char* name, const char* value) {
    if( s->count == s->capacity ) {
        size_t new_capacity = s->capacity * 2;
        if( new_capacity < INITIAL_STATS_CAPACITY )
            new_capacity = INITIAL_STATS_CAPACITY;
        yrmcds_cnt_stat* new_records =
            realloc(s->records, sizeof(yrmcds_cnt_stat) * new_capacity);
        if( new_records == NULL )
            return YRMCDS_OUT_OF_MEMORY;
        s->capacity = new_capacity;
        s->records = new_records;
    }

    s->records[s->count].name_length = name_len;
    s->records[s->count].value_length = value_len;
    s->records[s->count].name = name;
    s->records[s->count].value = value;
    s->count += 1;
    return YRMCDS_OK;
}