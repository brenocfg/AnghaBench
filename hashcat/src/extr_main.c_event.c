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
typedef  int u32 ;
typedef  int /*<<< orphan*/  hashcat_ctx_t ;

/* Variables and functions */
#define  EVENT_BACKEND_DEVICE_INIT_POST 173 
#define  EVENT_BACKEND_DEVICE_INIT_PRE 172 
#define  EVENT_BACKEND_SESSION_HOSTMEM 171 
#define  EVENT_BACKEND_SESSION_POST 170 
#define  EVENT_BACKEND_SESSION_PRE 169 
#define  EVENT_BITMAP_FINAL_OVERFLOW 168 
#define  EVENT_BITMAP_INIT_POST 167 
#define  EVENT_BITMAP_INIT_PRE 166 
#define  EVENT_CALCULATED_WORDS_BASE 165 
#define  EVENT_CRACKER_FINISHED 164 
#define  EVENT_CRACKER_HASH_CRACKED 163 
#define  EVENT_CRACKER_STARTING 162 
#define  EVENT_HASHLIST_COUNT_LINES_POST 161 
#define  EVENT_HASHLIST_COUNT_LINES_PRE 160 
#define  EVENT_HASHLIST_PARSE_HASH 159 
#define  EVENT_HASHLIST_SORT_HASH_POST 158 
#define  EVENT_HASHLIST_SORT_HASH_PRE 157 
#define  EVENT_HASHLIST_SORT_SALT_POST 156 
#define  EVENT_HASHLIST_SORT_SALT_PRE 155 
#define  EVENT_HASHLIST_UNIQUE_HASH_POST 154 
#define  EVENT_HASHLIST_UNIQUE_HASH_PRE 153 
#define  EVENT_LOG_ADVICE 152 
#define  EVENT_LOG_ERROR 151 
#define  EVENT_LOG_INFO 150 
#define  EVENT_LOG_WARNING 149 
#define  EVENT_MONITOR_NOINPUT_ABORT 148 
#define  EVENT_MONITOR_NOINPUT_HINT 147 
#define  EVENT_MONITOR_PERFORMANCE_HINT 146 
#define  EVENT_MONITOR_RUNTIME_LIMIT 145 
#define  EVENT_MONITOR_STATUS_REFRESH 144 
#define  EVENT_MONITOR_TEMP_ABORT 143 
#define  EVENT_MONITOR_THROTTLE1 142 
#define  EVENT_MONITOR_THROTTLE2 141 
#define  EVENT_MONITOR_THROTTLE3 140 
#define  EVENT_OUTERLOOP_FINISHED 139 
#define  EVENT_OUTERLOOP_MAINSCREEN 138 
#define  EVENT_OUTERLOOP_STARTING 137 
#define  EVENT_POTFILE_ALL_CRACKED 136 
#define  EVENT_POTFILE_HASH_LEFT 135 
#define  EVENT_POTFILE_HASH_SHOW 134 
#define  EVENT_POTFILE_NUM_CRACKED 133 
#define  EVENT_POTFILE_REMOVE_PARSE_POST 132 
#define  EVENT_POTFILE_REMOVE_PARSE_PRE 131 
#define  EVENT_SET_KERNEL_POWER_FINAL 130 
#define  EVENT_WORDLIST_CACHE_GENERATE 129 
#define  EVENT_WORDLIST_CACHE_HIT 128 
 int /*<<< orphan*/  main_backend_device_init_post (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_backend_device_init_pre (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_backend_session_hostmem (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_backend_session_post (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_backend_session_pre (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_bitmap_final_overflow (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_bitmap_init_post (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_bitmap_init_pre (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_calculated_words_base (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_cracker_finished (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_cracker_hash_cracked (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_cracker_starting (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_hashlist_count_lines_post (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_hashlist_count_lines_pre (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_hashlist_parse_hash (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_hashlist_sort_hash_post (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_hashlist_sort_hash_pre (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_hashlist_sort_salt_post (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_hashlist_sort_salt_pre (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_hashlist_unique_hash_post (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_hashlist_unique_hash_pre (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_log_advice (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_log_error (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_log_info (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_log_warning (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_monitor_noinput_abort (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_monitor_noinput_hint (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_monitor_performance_hint (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_monitor_runtime_limit (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_monitor_status_refresh (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_monitor_temp_abort (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_monitor_throttle1 (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_monitor_throttle2 (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_monitor_throttle3 (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_outerloop_finished (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_outerloop_mainscreen (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_outerloop_starting (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_potfile_all_cracked (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_potfile_hash_left (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_potfile_hash_show (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_potfile_num_cracked (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_potfile_remove_parse_post (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_potfile_remove_parse_pre (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_set_kernel_power_final (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_wordlist_cache_generate (int /*<<< orphan*/ *,void const*,size_t const) ; 
 int /*<<< orphan*/  main_wordlist_cache_hit (int /*<<< orphan*/ *,void const*,size_t const) ; 

__attribute__((used)) static void event (const u32 id, hashcat_ctx_t *hashcat_ctx, const void *buf, const size_t len)
{
  switch (id)
  {
    case EVENT_BITMAP_INIT_POST:          main_bitmap_init_post          (hashcat_ctx, buf, len); break;
    case EVENT_BITMAP_INIT_PRE:           main_bitmap_init_pre           (hashcat_ctx, buf, len); break;
    case EVENT_BITMAP_FINAL_OVERFLOW:     main_bitmap_final_overflow     (hashcat_ctx, buf, len); break;
    case EVENT_CALCULATED_WORDS_BASE:     main_calculated_words_base     (hashcat_ctx, buf, len); break;
    case EVENT_CRACKER_FINISHED:          main_cracker_finished          (hashcat_ctx, buf, len); break;
    case EVENT_CRACKER_HASH_CRACKED:      main_cracker_hash_cracked      (hashcat_ctx, buf, len); break;
    case EVENT_CRACKER_STARTING:          main_cracker_starting          (hashcat_ctx, buf, len); break;
    case EVENT_HASHLIST_COUNT_LINES_POST: main_hashlist_count_lines_post (hashcat_ctx, buf, len); break;
    case EVENT_HASHLIST_COUNT_LINES_PRE:  main_hashlist_count_lines_pre  (hashcat_ctx, buf, len); break;
    case EVENT_HASHLIST_PARSE_HASH:       main_hashlist_parse_hash       (hashcat_ctx, buf, len); break;
    case EVENT_HASHLIST_SORT_HASH_POST:   main_hashlist_sort_hash_post   (hashcat_ctx, buf, len); break;
    case EVENT_HASHLIST_SORT_HASH_PRE:    main_hashlist_sort_hash_pre    (hashcat_ctx, buf, len); break;
    case EVENT_HASHLIST_SORT_SALT_POST:   main_hashlist_sort_salt_post   (hashcat_ctx, buf, len); break;
    case EVENT_HASHLIST_SORT_SALT_PRE:    main_hashlist_sort_salt_pre    (hashcat_ctx, buf, len); break;
    case EVENT_HASHLIST_UNIQUE_HASH_POST: main_hashlist_unique_hash_post (hashcat_ctx, buf, len); break;
    case EVENT_HASHLIST_UNIQUE_HASH_PRE:  main_hashlist_unique_hash_pre  (hashcat_ctx, buf, len); break;
    case EVENT_LOG_ERROR:                 main_log_error                 (hashcat_ctx, buf, len); break;
    case EVENT_LOG_INFO:                  main_log_info                  (hashcat_ctx, buf, len); break;
    case EVENT_LOG_WARNING:               main_log_warning               (hashcat_ctx, buf, len); break;
    case EVENT_LOG_ADVICE:                main_log_advice                (hashcat_ctx, buf, len); break;
    case EVENT_MONITOR_RUNTIME_LIMIT:     main_monitor_runtime_limit     (hashcat_ctx, buf, len); break;
    case EVENT_MONITOR_STATUS_REFRESH:    main_monitor_status_refresh    (hashcat_ctx, buf, len); break;
    case EVENT_MONITOR_TEMP_ABORT:        main_monitor_temp_abort        (hashcat_ctx, buf, len); break;
    case EVENT_MONITOR_THROTTLE1:         main_monitor_throttle1         (hashcat_ctx, buf, len); break;
    case EVENT_MONITOR_THROTTLE2:         main_monitor_throttle2         (hashcat_ctx, buf, len); break;
    case EVENT_MONITOR_THROTTLE3:         main_monitor_throttle3         (hashcat_ctx, buf, len); break;
    case EVENT_MONITOR_PERFORMANCE_HINT:  main_monitor_performance_hint  (hashcat_ctx, buf, len); break;
    case EVENT_MONITOR_NOINPUT_HINT:      main_monitor_noinput_hint      (hashcat_ctx, buf, len); break;
    case EVENT_MONITOR_NOINPUT_ABORT:     main_monitor_noinput_abort     (hashcat_ctx, buf, len); break;
    case EVENT_BACKEND_SESSION_POST:      main_backend_session_post      (hashcat_ctx, buf, len); break;
    case EVENT_BACKEND_SESSION_PRE:       main_backend_session_pre       (hashcat_ctx, buf, len); break;
    case EVENT_BACKEND_SESSION_HOSTMEM:   main_backend_session_hostmem   (hashcat_ctx, buf, len); break;
    case EVENT_BACKEND_DEVICE_INIT_POST:  main_backend_device_init_post  (hashcat_ctx, buf, len); break;
    case EVENT_BACKEND_DEVICE_INIT_PRE:   main_backend_device_init_pre   (hashcat_ctx, buf, len); break;
    case EVENT_OUTERLOOP_FINISHED:        main_outerloop_finished        (hashcat_ctx, buf, len); break;
    case EVENT_OUTERLOOP_MAINSCREEN:      main_outerloop_mainscreen      (hashcat_ctx, buf, len); break;
    case EVENT_OUTERLOOP_STARTING:        main_outerloop_starting        (hashcat_ctx, buf, len); break;
    case EVENT_POTFILE_ALL_CRACKED:       main_potfile_all_cracked       (hashcat_ctx, buf, len); break;
    case EVENT_POTFILE_HASH_LEFT:         main_potfile_hash_left         (hashcat_ctx, buf, len); break;
    case EVENT_POTFILE_HASH_SHOW:         main_potfile_hash_show         (hashcat_ctx, buf, len); break;
    case EVENT_POTFILE_NUM_CRACKED:       main_potfile_num_cracked       (hashcat_ctx, buf, len); break;
    case EVENT_POTFILE_REMOVE_PARSE_POST: main_potfile_remove_parse_post (hashcat_ctx, buf, len); break;
    case EVENT_POTFILE_REMOVE_PARSE_PRE:  main_potfile_remove_parse_pre  (hashcat_ctx, buf, len); break;
    case EVENT_SET_KERNEL_POWER_FINAL:    main_set_kernel_power_final    (hashcat_ctx, buf, len); break;
    case EVENT_WORDLIST_CACHE_GENERATE:   main_wordlist_cache_generate   (hashcat_ctx, buf, len); break;
    case EVENT_WORDLIST_CACHE_HIT:        main_wordlist_cache_hit        (hashcat_ctx, buf, len); break;
  }
}