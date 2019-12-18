#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ _position; scalar_t__ _limit; } ;
typedef  TYPE_1__ sldns_buffer ;

/* Variables and functions */
 scalar_t__ sldns_buffer_available_at (TYPE_1__*,scalar_t__,int) ; 
 scalar_t__ sldns_buffer_read_u8_at (TYPE_1__*,scalar_t__) ; 

void
sldns_bskipcs(sldns_buffer *buffer, const char *s)
{
        int found;
        char c;
        const char *d;

        while(sldns_buffer_available_at(buffer, buffer->_position, sizeof(char))) {
                c = (char) sldns_buffer_read_u8_at(buffer, buffer->_position);
                found = 0;
                for (d = s; *d; d++) {
                        if (*d == c) {
                                found = 1;
                        }
                }
                if (found && buffer->_limit > buffer->_position) {
                        buffer->_position += sizeof(char);
                } else {
                        return;
                }
        }
}