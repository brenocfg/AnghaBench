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
typedef  scalar_t__ index_type ;
struct TYPE_5__ {scalar_t__ count; } ;
typedef  int /*<<< orphan*/  Line ;
typedef  TYPE_1__ HistoryBuf ;

/* Variables and functions */
 int /*<<< orphan*/  index_of (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  init_line (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline Line*
get_line(HistoryBuf *self, index_type y, Line *l) { init_line(self, index_of(self, self->count - y - 1), l); return l; }