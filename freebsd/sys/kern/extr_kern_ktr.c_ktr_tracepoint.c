#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint64_t ;
typedef  void* u_long ;
struct thread {int td_pflags; scalar_t__ td_critnest; } ;
struct ktr_entry {int ktr_cpu; char const* ktr_file; int ktr_line; char const* ktr_desc; void** ktr_parms; void* ktr_thread; int /*<<< orphan*/  ktr_timestamp; } ;
struct ale {scalar_t__ ae_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALQ_NOWAIT ; 
 int /*<<< orphan*/  CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int KTR_CPU ; 
 int /*<<< orphan*/  KTR_TIME ; 
 int TDP_INKTR ; 
 scalar_t__ TD_IS_IDLETHREAD (struct thread*) ; 
 struct thread* ald_thread ; 
 struct ale* alq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alq_post (int /*<<< orphan*/ ,struct ale*) ; 
 scalar_t__ atomic_cmpset_rel_int (int*,int,int) ; 
 void* curthread ; 
 scalar_t__ kdb_active ; 
 int /*<<< orphan*/  ktr_alq ; 
 scalar_t__ ktr_alq_cnt ; 
 scalar_t__ ktr_alq_enabled ; 
 int /*<<< orphan*/  ktr_alq_failed ; 
 scalar_t__ ktr_alq_max ; 
 struct ktr_entry* ktr_buf ; 
 int /*<<< orphan*/  ktr_cpumask ; 
 int ktr_entries ; 
 int ktr_idx ; 
 int ktr_mask ; 
 int ktr_verbose ; 
 scalar_t__ panicstr ; 
 int /*<<< orphan*/  printf (char const*,...) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

void
ktr_tracepoint(uint64_t mask, const char *file, int line, const char *format,
    u_long arg1, u_long arg2, u_long arg3, u_long arg4, u_long arg5,
    u_long arg6)
{
	struct ktr_entry *entry;
#ifdef KTR_ALQ
	struct ale *ale = NULL;
#endif
	int newindex, saveindex;
#if defined(KTR_VERBOSE) || defined(KTR_ALQ)
	struct thread *td;
#endif
	int cpu;

	if (panicstr || kdb_active)
		return;
	if ((ktr_mask & mask) == 0 || ktr_buf == NULL)
		return;
	cpu = KTR_CPU;
	if (!CPU_ISSET(cpu, &ktr_cpumask))
		return;
#if defined(KTR_VERBOSE) || defined(KTR_ALQ)
	td = curthread;
	if (td->td_pflags & TDP_INKTR)
		return;
	td->td_pflags |= TDP_INKTR;
#endif
#ifdef KTR_ALQ
	if (ktr_alq_enabled) {
		if (td->td_critnest == 0 &&
		    (TD_IS_IDLETHREAD(td)) == 0 &&
		    td != ald_thread) {
			if (ktr_alq_max && ktr_alq_cnt > ktr_alq_max)
				goto done;
			if ((ale = alq_get(ktr_alq, ALQ_NOWAIT)) == NULL) {
				ktr_alq_failed++;
				goto done;
			}
			ktr_alq_cnt++;
			entry = (struct ktr_entry *)ale->ae_data;
		} else {
			goto done;
		}
	} else
#endif
	{
		do {
			saveindex = ktr_idx;
			newindex = (saveindex + 1) % ktr_entries;
		} while (atomic_cmpset_rel_int(&ktr_idx, saveindex, newindex) == 0);
		entry = &ktr_buf[saveindex];
	}
	entry->ktr_timestamp = KTR_TIME;
	entry->ktr_cpu = cpu;
	entry->ktr_thread = curthread;
	if (file != NULL)
		while (strncmp(file, "../", 3) == 0)
			file += 3;
	entry->ktr_file = file;
	entry->ktr_line = line;
#ifdef KTR_VERBOSE
	if (ktr_verbose) {
#ifdef SMP
		printf("cpu%d ", cpu);
#endif
		if (ktr_verbose > 1) {
			printf("%s.%d\t", entry->ktr_file,
			    entry->ktr_line);
		}
		printf(format, arg1, arg2, arg3, arg4, arg5, arg6);
		printf("\n");
	}
#endif
	entry->ktr_desc = format;
	entry->ktr_parms[0] = arg1;
	entry->ktr_parms[1] = arg2;
	entry->ktr_parms[2] = arg3;
	entry->ktr_parms[3] = arg4;
	entry->ktr_parms[4] = arg5;
	entry->ktr_parms[5] = arg6;
#ifdef KTR_ALQ
	if (ktr_alq_enabled && ale)
		alq_post(ktr_alq, ale);
done:
#endif
#if defined(KTR_VERBOSE) || defined(KTR_ALQ)
	td->td_pflags &= ~TDP_INKTR;
#endif
}